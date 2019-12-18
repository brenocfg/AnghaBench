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
struct nfp_cpp_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_cpp_area_free (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  nfp_cpp_area_release (struct nfp_cpp_area*) ; 

void nfp_cpp_area_release_free(struct nfp_cpp_area *area)
{
	nfp_cpp_area_release(area);
	nfp_cpp_area_free(area);
}