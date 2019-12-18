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
struct s6e63j0x03 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_LEVEL2_KEY ; 
 int s6e63j0x03_dcs_write_seq_static (struct s6e63j0x03*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int s6e63j0x03_enable_lv2_command(struct s6e63j0x03 *ctx)
{
	return s6e63j0x03_dcs_write_seq_static(ctx, MCS_LEVEL2_KEY, 0x5a, 0x5a);
}