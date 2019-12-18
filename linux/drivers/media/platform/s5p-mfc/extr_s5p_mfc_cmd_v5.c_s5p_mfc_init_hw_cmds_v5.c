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
struct s5p_mfc_hw_cmds {int dummy; } ;

/* Variables and functions */
 struct s5p_mfc_hw_cmds s5p_mfc_cmds_v5 ; 

struct s5p_mfc_hw_cmds *s5p_mfc_init_hw_cmds_v5(void)
{
	return &s5p_mfc_cmds_v5;
}