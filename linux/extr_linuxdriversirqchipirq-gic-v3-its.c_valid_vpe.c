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
struct its_vpe {scalar_t__ col_idx; } ;
struct its_node {scalar_t__ collections; } ;

/* Variables and functions */
 scalar_t__ valid_col (scalar_t__) ; 

__attribute__((used)) static struct its_vpe *valid_vpe(struct its_node *its, struct its_vpe *vpe)
{
	if (valid_col(its->collections + vpe->col_idx))
		return vpe;

	return NULL;
}