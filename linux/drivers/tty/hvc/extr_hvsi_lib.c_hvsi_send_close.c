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
struct hvsi_priv {scalar_t__ established; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  type; } ;
struct hvsi_control {TYPE_1__ hdr; int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSV_CLOSE_PROTOCOL ; 
 int /*<<< orphan*/  VS_CONTROL_PACKET_HEADER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int hvsi_send_packet (struct hvsi_priv*,TYPE_1__*) ; 

__attribute__((used)) static int hvsi_send_close(struct hvsi_priv *pv)
{
	struct hvsi_control ctrl;

	pv->established = 0;

	ctrl.hdr.type = VS_CONTROL_PACKET_HEADER;
	ctrl.hdr.len = sizeof(struct hvsi_control);
	ctrl.verb = cpu_to_be16(VSV_CLOSE_PROTOCOL);
	return hvsi_send_packet(pv, &ctrl.hdr);
}