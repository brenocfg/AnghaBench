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
struct pblk_line {int dummy; } ;
struct TYPE_2__ {struct pblk_line* data_line; } ;
struct pblk {TYPE_1__ l_mg; } ;

/* Variables and functions */

struct pblk_line *pblk_line_get_data(struct pblk *pblk)
{
	return pblk->l_mg.data_line;
}