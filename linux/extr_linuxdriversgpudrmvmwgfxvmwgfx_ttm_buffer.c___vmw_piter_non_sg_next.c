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
struct vmw_piter {scalar_t__ i; scalar_t__ num_pages; } ;

/* Variables and functions */

__attribute__((used)) static bool __vmw_piter_non_sg_next(struct vmw_piter *viter)
{
	return ++(viter->i) < viter->num_pages;
}