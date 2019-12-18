#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct cxl_afu {int pp_size; int crs_len; int eb_len; int /*<<< orphan*/  dev; int /*<<< orphan*/  eb_offset; int /*<<< orphan*/  crs_offset; TYPE_1__* native; int /*<<< orphan*/  pp_psa; int /*<<< orphan*/  psa; int /*<<< orphan*/  modes_supported; int /*<<< orphan*/  crs_num; int /*<<< orphan*/  max_procs_virtualised; int /*<<< orphan*/  pp_irqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pp_offset; } ;

/* Variables and functions */
 scalar_t__ AFUD_AFU_DIRECTED (int /*<<< orphan*/ ) ; 
 int AFUD_CR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ AFUD_DEDICATED_PROCESS (int /*<<< orphan*/ ) ; 
 int AFUD_EB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_NUM_CRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_NUM_INTS_PER_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_NUM_PROCS (int /*<<< orphan*/ ) ; 
 int AFUD_PPPSA_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_PPPSA_PP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_PPPSA_PSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFUD_READ_CR (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_CR_OFF (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_EB (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_EB_OFF (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_INFO (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_PPPSA (struct cxl_afu*) ; 
 int /*<<< orphan*/  AFUD_READ_PPPSA_OFF (struct cxl_afu*) ; 
 scalar_t__ AFUD_TIME_SLICED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXL_MODE_DEDICATED ; 
 int /*<<< orphan*/  CXL_MODE_DIRECTED ; 
 int /*<<< orphan*/  CXL_MODE_TIME_SLICED ; 
 scalar_t__ EXTRACT_PPC_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxl_read_afu_descriptor(struct cxl_afu *afu)
{
	u64 val;

	val = AFUD_READ_INFO(afu);
	afu->pp_irqs = AFUD_NUM_INTS_PER_PROC(val);
	afu->max_procs_virtualised = AFUD_NUM_PROCS(val);
	afu->crs_num = AFUD_NUM_CRS(val);

	if (AFUD_AFU_DIRECTED(val))
		afu->modes_supported |= CXL_MODE_DIRECTED;
	if (AFUD_DEDICATED_PROCESS(val))
		afu->modes_supported |= CXL_MODE_DEDICATED;
	if (AFUD_TIME_SLICED(val))
		afu->modes_supported |= CXL_MODE_TIME_SLICED;

	val = AFUD_READ_PPPSA(afu);
	afu->pp_size = AFUD_PPPSA_LEN(val) * 4096;
	afu->psa = AFUD_PPPSA_PSA(val);
	if ((afu->pp_psa = AFUD_PPPSA_PP(val)))
		afu->native->pp_offset = AFUD_READ_PPPSA_OFF(afu);

	val = AFUD_READ_CR(afu);
	afu->crs_len = AFUD_CR_LEN(val) * 256;
	afu->crs_offset = AFUD_READ_CR_OFF(afu);


	/* eb_len is in multiple of 4K */
	afu->eb_len = AFUD_EB_LEN(AFUD_READ_EB(afu)) * 4096;
	afu->eb_offset = AFUD_READ_EB_OFF(afu);

	/* eb_off is 4K aligned so lower 12 bits are always zero */
	if (EXTRACT_PPC_BITS(afu->eb_offset, 0, 11) != 0) {
		dev_warn(&afu->dev,
			 "Invalid AFU error buffer offset %Lx\n",
			 afu->eb_offset);
		dev_info(&afu->dev,
			 "Ignoring AFU error buffer in the descriptor\n");
		/* indicate that no afu buffer exists */
		afu->eb_len = 0;
	}

	return 0;
}