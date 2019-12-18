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
struct v4l2_audio {scalar_t__ index; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pvr2_enumaudio(struct file *file, void *priv, struct v4l2_audio *vin)
{
	/* pkt: FIXME: We are returning one "fake" input here
	   which could very well be called "whatever_we_like".
	   This is for apps that want to see an audio input
	   just to feel comfortable, as well as to test if
	   it can do stereo or sth. There is actually no guarantee
	   that the actual audio input cannot change behind the app's
	   back, but most applications should not mind that either.

	   Hopefully, mplayer people will work with us on this (this
	   whole mess is to support mplayer pvr://), or Hans will come
	   up with a more standard way to say "we have inputs but we
	   don 't want you to change them independent of video" which
	   will sort this mess.
	 */

	if (vin->index > 0)
		return -EINVAL;
	strscpy(vin->name, "PVRUSB2 Audio", sizeof(vin->name));
	vin->capability = V4L2_AUDCAP_STEREO;
	return 0;
}