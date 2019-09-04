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
struct s6e8aa0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq_static (struct s6e8aa0*,int,int,int) ; 

__attribute__((used)) static void s6e8aa0_apply_level_1_key(struct s6e8aa0 *ctx)
{
	s6e8aa0_dcs_write_seq_static(ctx, 0xf0, 0x5a, 0x5a);
}