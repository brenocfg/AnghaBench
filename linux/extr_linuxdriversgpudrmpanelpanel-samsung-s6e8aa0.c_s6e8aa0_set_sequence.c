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
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq_static (struct s6e8aa0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e8aa0_panel_init (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_read_mtp_id (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_set_maximum_return_packet_size (struct s6e8aa0*,int) ; 

__attribute__((used)) static void s6e8aa0_set_sequence(struct s6e8aa0 *ctx)
{
	s6e8aa0_set_maximum_return_packet_size(ctx, 3);
	s6e8aa0_read_mtp_id(ctx);
	s6e8aa0_panel_init(ctx);
	s6e8aa0_dcs_write_seq_static(ctx, MIPI_DCS_SET_DISPLAY_ON);
}