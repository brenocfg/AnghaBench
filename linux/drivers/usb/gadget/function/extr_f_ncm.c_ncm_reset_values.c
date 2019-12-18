#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fixed_in_len; int /*<<< orphan*/  fixed_out_len; scalar_t__ header_len; int /*<<< orphan*/  cdc_filter; } ;
struct f_ncm {int is_crc; TYPE_1__ port; TYPE_3__* parser_opts; int /*<<< orphan*/  ndp_sign; } ;
struct TYPE_6__ {int /*<<< orphan*/  ndp_sign; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwNtbOutMaxSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FILTER ; 
 int /*<<< orphan*/  NTB_DEFAULT_IN_SIZE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__ ndp16_opts ; 
 TYPE_2__ ntb_parameters ; 

__attribute__((used)) static inline void ncm_reset_values(struct f_ncm *ncm)
{
	ncm->parser_opts = &ndp16_opts;
	ncm->is_crc = false;
	ncm->ndp_sign = ncm->parser_opts->ndp_sign;
	ncm->port.cdc_filter = DEFAULT_FILTER;

	/* doesn't make sense for ncm, fixed size used */
	ncm->port.header_len = 0;

	ncm->port.fixed_out_len = le32_to_cpu(ntb_parameters.dwNtbOutMaxSize);
	ncm->port.fixed_in_len = NTB_DEFAULT_IN_SIZE;
}