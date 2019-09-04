#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIO_BOOT_LOC_ADR ; 
 int /*<<< orphan*/  CVMX_MIO_BOOT_LOC_CFGX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MIO_BOOT_LOC_DAT ; 
 scalar_t__ OCTEON_IS_OCTEON1PLUS () ; 
 int /*<<< orphan*/  VECTOR_TABLE_SIZE ; 
 int* _cvmx_bootvector_data ; 
 int cvmx_ptr_to_phys (void*) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvmx_boot_vector_init(void *mem)
{
	uint64_t kseg0_mem;
	int i;

	memset(mem, 0, VECTOR_TABLE_SIZE);
	kseg0_mem = cvmx_ptr_to_phys(mem) | 0x8000000000000000ull;

	for (i = 0; i < 15; i++) {
		uint64_t v = _cvmx_bootvector_data[i];

		if (OCTEON_IS_OCTEON1PLUS() && (i == 0 || i == 7))
			v &= 0xffffffff00000000ull; /* KScratch not availble. */
		cvmx_write_csr(CVMX_MIO_BOOT_LOC_ADR, i * 8);
		cvmx_write_csr(CVMX_MIO_BOOT_LOC_DAT, v);
	}
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_ADR, 15 * 8);
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_DAT, kseg0_mem);
	cvmx_write_csr(CVMX_MIO_BOOT_LOC_CFGX(0), 0x81fc0000);
}