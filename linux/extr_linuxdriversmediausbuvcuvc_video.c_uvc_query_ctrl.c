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
typedef  int u8 ;
typedef  int u16 ;
struct uvc_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EILSEQ ; 
 int EINVAL ; 
 int EPIPE ; 
 int ERANGE ; 
 int EREMOTE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  UVC_CTRL_CONTROL_TIMEOUT ; 
 int UVC_GET_CUR ; 
 int /*<<< orphan*/  UVC_TRACE_CONTROL ; 
 int UVC_VC_REQUEST_ERROR_CODE_CONTROL ; 
 int __uvc_query_ctrl (struct uvc_device*,int,int,int,int,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  uvc_query_name (int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int) ; 

int uvc_query_ctrl(struct uvc_device *dev, u8 query, u8 unit,
			u8 intfnum, u8 cs, void *data, u16 size)
{
	int ret;
	u8 error;
	u8 tmp;

	ret = __uvc_query_ctrl(dev, query, unit, intfnum, cs, data, size,
				UVC_CTRL_CONTROL_TIMEOUT);
	if (likely(ret == size))
		return 0;

	uvc_printk(KERN_ERR,
		   "Failed to query (%s) UVC control %u on unit %u: %d (exp. %u).\n",
		   uvc_query_name(query), cs, unit, ret, size);

	if (ret != -EPIPE)
		return ret;

	tmp = *(u8 *)data;

	ret = __uvc_query_ctrl(dev, UVC_GET_CUR, 0, intfnum,
			       UVC_VC_REQUEST_ERROR_CODE_CONTROL, data, 1,
			       UVC_CTRL_CONTROL_TIMEOUT);

	error = *(u8 *)data;
	*(u8 *)data = tmp;

	if (ret != 1)
		return ret < 0 ? ret : -EPIPE;

	uvc_trace(UVC_TRACE_CONTROL, "Control error %u\n", error);

	switch (error) {
	case 0:
		/* Cannot happen - we received a STALL */
		return -EPIPE;
	case 1: /* Not ready */
		return -EBUSY;
	case 2: /* Wrong state */
		return -EILSEQ;
	case 3: /* Power */
		return -EREMOTE;
	case 4: /* Out of range */
		return -ERANGE;
	case 5: /* Invalid unit */
	case 6: /* Invalid control */
	case 7: /* Invalid Request */
	case 8: /* Invalid value within range */
		return -EINVAL;
	default: /* reserved or unknown */
		break;
	}

	return -EPIPE;
}