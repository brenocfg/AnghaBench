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
struct wm97xx_priv {int /*<<< orphan*/  ac97; } ;
struct ac97_codec_device {int dummy; } ;

/* Variables and functions */
 struct wm97xx_priv* ac97_get_drvdata (struct ac97_codec_device*) ; 
 int /*<<< orphan*/  snd_ac97_compat_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm97xx_ac97_remove(struct ac97_codec_device *adev)
{
	struct wm97xx_priv *wm97xx = ac97_get_drvdata(adev);

	snd_ac97_compat_release(wm97xx->ac97);

	return 0;
}