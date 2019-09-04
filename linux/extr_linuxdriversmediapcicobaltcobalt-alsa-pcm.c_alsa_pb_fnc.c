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
struct vb2_buffer {int dummy; } ;
struct cobalt_stream {TYPE_1__* alsa; } ;
struct TYPE_2__ {scalar_t__ alsa_pb_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_alsa_pb_pcm_data (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alsa_pb_fnc(struct vb2_buffer *vb, void *priv)
{
	struct cobalt_stream *s = priv;

	if (s->alsa->alsa_pb_channel)
		cobalt_alsa_pb_pcm_data(s->alsa,
				vb2_plane_vaddr(vb, 0),
				8 * 4,
				vb2_get_plane_payload(vb, 0) / (8 * 4));
	return 0;
}