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
struct vc_data {int vc_cols; } ;

/* Variables and functions */
 int /*<<< orphan*/  announce_edge (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edge_right ; 
 int /*<<< orphan*/  say_char (struct vc_data*) ; 
 int spk_parked ; 
 int spk_pos ; 
 int spk_x ; 

__attribute__((used)) static void say_next_char(struct vc_data *vc)
{
	spk_parked |= 0x01;
	if (spk_x == vc->vc_cols - 1) {
		announce_edge(vc, edge_right);
		return;
	}
	spk_x++;
	spk_pos += 2;
	say_char(vc);
}