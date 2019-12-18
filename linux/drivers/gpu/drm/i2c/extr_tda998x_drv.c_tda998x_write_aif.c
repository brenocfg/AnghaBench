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
struct hdmi_audio_infoframe {int dummy; } ;
union hdmi_infoframe {struct hdmi_audio_infoframe audio; } ;
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIP_IF_FLAGS_IF4 ; 
 int /*<<< orphan*/  REG_IF4_HB0 ; 
 int /*<<< orphan*/  tda998x_write_if (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union hdmi_infoframe*) ; 

__attribute__((used)) static void tda998x_write_aif(struct tda998x_priv *priv,
			      const struct hdmi_audio_infoframe *cea)
{
	union hdmi_infoframe frame;

	frame.audio = *cea;

	tda998x_write_if(priv, DIP_IF_FLAGS_IF4, REG_IF4_HB0, &frame);
}