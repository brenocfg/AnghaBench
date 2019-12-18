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
struct vc_data {int vc_rows; scalar_t__ vc_size_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  announce_edge (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edge_bottom ; 
 int /*<<< orphan*/  say_line (struct vc_data*) ; 
 int spk_parked ; 
 int /*<<< orphan*/  spk_pos ; 
 int spk_y ; 

__attribute__((used)) static void say_next_line(struct vc_data *vc)
{
	spk_parked |= 0x01;
	if (spk_y == vc->vc_rows - 1) {
		announce_edge(vc, edge_bottom);
		return;
	}
	spk_y++;
	spk_pos += vc->vc_size_row;
	say_line(vc);
}