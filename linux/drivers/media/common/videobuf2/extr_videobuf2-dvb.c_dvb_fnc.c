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
struct vb2_dvb {int /*<<< orphan*/  demux; } ;
struct vb2_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_fnc(struct vb2_buffer *vb, void *priv)
{
	struct vb2_dvb *dvb = priv;

	dvb_dmx_swfilter(&dvb->demux, vb2_plane_vaddr(vb, 0),
				      vb2_get_plane_payload(vb, 0));
	return 0;
}