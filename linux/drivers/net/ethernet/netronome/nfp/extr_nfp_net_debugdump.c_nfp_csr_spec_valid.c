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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct nfp_dumpspec_csr {int /*<<< orphan*/  register_width; TYPE_1__ tl; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfp_csr_spec_valid(struct nfp_dumpspec_csr *spec_csr)
{
	u32 required_read_sz = sizeof(*spec_csr) - sizeof(spec_csr->tl);
	u32 available_sz = be32_to_cpu(spec_csr->tl.length);
	u32 reg_width;

	if (available_sz < required_read_sz)
		return false;

	reg_width = be32_to_cpu(spec_csr->register_width);

	return reg_width == 32 || reg_width == 64;
}