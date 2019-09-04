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
struct input_dev {int dummy; } ;
struct iforce_core_effect {int /*<<< orphan*/  flags; } ;
struct iforce {struct iforce_core_effect* core_effects; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CORE_SHOULD_PLAY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iforce_control_playback (struct iforce*,int,int) ; 
 struct iforce* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iforce_playback(struct input_dev *dev, int effect_id, int value)
{
	struct iforce *iforce = input_get_drvdata(dev);
	struct iforce_core_effect *core_effect = &iforce->core_effects[effect_id];

	if (value > 0)
		set_bit(FF_CORE_SHOULD_PLAY, core_effect->flags);
	else
		clear_bit(FF_CORE_SHOULD_PLAY, core_effect->flags);

	iforce_control_playback(iforce, effect_id, value);
	return 0;
}