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
typedef  scalar_t__ u32 ;
struct stimx274 {TYPE_1__* mode; } ;
struct TYPE_2__ {scalar_t__ min_frame_len; scalar_t__ min_SHR; } ;

/* Variables and functions */
 scalar_t__ IMX274_SHR_LIMIT_CONST ; 
 int imx274_get_frame_length (struct stimx274*,scalar_t__*) ; 

__attribute__((used)) static int imx274_clamp_coarse_time(struct stimx274 *priv, u32 *val,
				    u32 *frame_length)
{
	int err;

	err = imx274_get_frame_length(priv, frame_length);
	if (err)
		return err;

	if (*frame_length < priv->mode->min_frame_len)
		*frame_length =  priv->mode->min_frame_len;

	*val = *frame_length - *val; /* convert to raw shr */
	if (*val > *frame_length - IMX274_SHR_LIMIT_CONST)
		*val = *frame_length - IMX274_SHR_LIMIT_CONST;
	else if (*val < priv->mode->min_SHR)
		*val = priv->mode->min_SHR;

	return 0;
}