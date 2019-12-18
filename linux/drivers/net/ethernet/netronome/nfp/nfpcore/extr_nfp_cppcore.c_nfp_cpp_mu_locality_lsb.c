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
struct nfp_cpp {unsigned int mu_locality_lsb; } ;

/* Variables and functions */

unsigned int nfp_cpp_mu_locality_lsb(struct nfp_cpp *cpp)
{
	return cpp->mu_locality_lsb;
}