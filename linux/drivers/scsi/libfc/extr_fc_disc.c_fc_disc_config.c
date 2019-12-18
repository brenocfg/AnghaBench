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
struct fc_disc {void* priv; } ;
struct TYPE_2__ {scalar_t__ disc_recv_req; scalar_t__ disc_stop_final; scalar_t__ disc_stop; scalar_t__ disc_start; } ;
struct fc_lport {struct fc_disc disc; TYPE_1__ tt; } ;

/* Variables and functions */
 scalar_t__ fc_disc_recv_req ; 
 scalar_t__ fc_disc_start ; 
 scalar_t__ fc_disc_stop ; 
 scalar_t__ fc_disc_stop_final ; 

void fc_disc_config(struct fc_lport *lport, void *priv)
{
	struct fc_disc *disc;

	if (!lport->tt.disc_start)
		lport->tt.disc_start = fc_disc_start;

	if (!lport->tt.disc_stop)
		lport->tt.disc_stop = fc_disc_stop;

	if (!lport->tt.disc_stop_final)
		lport->tt.disc_stop_final = fc_disc_stop_final;

	if (!lport->tt.disc_recv_req)
		lport->tt.disc_recv_req = fc_disc_recv_req;

	disc = &lport->disc;

	disc->priv = priv;
}