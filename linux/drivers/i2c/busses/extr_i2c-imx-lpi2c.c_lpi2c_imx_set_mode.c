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
struct lpi2c_imx_struct {unsigned int bitrate; int mode; } ;
typedef  enum lpi2c_imx_mode { ____Placeholder_lpi2c_imx_mode } lpi2c_imx_mode ;

/* Variables and functions */
 int FAST ; 
 unsigned int FAST_MAX_BITRATE ; 
 int FAST_PLUS ; 
 unsigned int FAST_PLUS_MAX_BITRATE ; 
 unsigned int HIGHSPEED_MAX_BITRATE ; 
 int HS ; 
 int STANDARD ; 
 unsigned int STARDARD_MAX_BITRATE ; 
 int ULTRA_FAST ; 

__attribute__((used)) static void lpi2c_imx_set_mode(struct lpi2c_imx_struct *lpi2c_imx)
{
	unsigned int bitrate = lpi2c_imx->bitrate;
	enum lpi2c_imx_mode mode;

	if (bitrate < STARDARD_MAX_BITRATE)
		mode = STANDARD;
	else if (bitrate < FAST_MAX_BITRATE)
		mode = FAST;
	else if (bitrate < FAST_PLUS_MAX_BITRATE)
		mode = FAST_PLUS;
	else if (bitrate < HIGHSPEED_MAX_BITRATE)
		mode = HS;
	else
		mode = ULTRA_FAST;

	lpi2c_imx->mode = mode;
}