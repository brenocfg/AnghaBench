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
typedef  int u8 ;
struct tda998x_priv {int tmds_clock; TYPE_1__* hdmi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUDIO_DIV_SERCLK_1 ; 
 int AUDIO_DIV_SERCLK_32 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned int,unsigned long,int) ; 

__attribute__((used)) static u8 tda998x_get_adiv(struct tda998x_priv *priv, unsigned int fs)
{
	unsigned long min_audio_clk = fs * 128;
	unsigned long ser_clk = priv->tmds_clock * 1000;
	u8 adiv;

	for (adiv = AUDIO_DIV_SERCLK_32; adiv != AUDIO_DIV_SERCLK_1; adiv--)
		if (ser_clk > min_audio_clk << adiv)
			break;

	dev_dbg(&priv->hdmi->dev,
		"ser_clk=%luHz fs=%uHz min_aclk=%luHz adiv=%d\n",
		ser_clk, fs, min_audio_clk, adiv);

	return adiv;
}