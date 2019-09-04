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
struct vb2_buffer {int dummy; } ;
struct cobalt_stream {int /*<<< orphan*/  alsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_alsa_announce_pcm_data (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 scalar_t__ pcm_debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 unsigned char* vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alsa_fnc(struct vb2_buffer *vb, void *priv)
{
	struct cobalt_stream *s = priv;
	unsigned char *p = vb2_plane_vaddr(vb, 0);
	int i;

	if (pcm_debug) {
		pr_info("alsa: ");
		for (i = 0; i < 8 * 4; i++) {
			if (!(i & 3))
				pr_cont(" ");
			pr_cont("%02x", p[i]);
		}
		pr_cont("\n");
	}
	cobalt_alsa_announce_pcm_data(s->alsa,
			vb2_plane_vaddr(vb, 0),
			8 * 4,
			vb2_get_plane_payload(vb, 0) / (8 * 4));
	return 0;
}