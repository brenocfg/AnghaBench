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
struct s6e3ha2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s6e3ha2_dcs_write_seq_static (struct s6e3ha2*,int,int,int) ; 

__attribute__((used)) static int s6e3ha2_test_key_off_f0(struct s6e3ha2 *ctx)
{
	s6e3ha2_dcs_write_seq_static(ctx, 0xf0, 0xa5, 0xa5);
	return 0;
}