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
typedef  union atto_ioctl_csmi {int dummy; } atto_ioctl_csmi ;
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_buffered_ioctl {int length; struct atto_csmi* done_context; int /*<<< orphan*/  done_callback; struct atto_csmi* context; int /*<<< orphan*/  callback; scalar_t__ offset; int /*<<< orphan*/ * ioctl; struct esas2r_adapter* a; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_csmi {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  bi ;

/* Variables and functions */
 int /*<<< orphan*/  csmi_ioctl_callback ; 
 int /*<<< orphan*/  csmi_ioctl_done_callback ; 
 int /*<<< orphan*/  handle_buffered_ioctl (struct esas2r_buffered_ioctl*) ; 
 int /*<<< orphan*/  memset (struct esas2r_buffered_ioctl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 handle_csmi_ioctl(struct esas2r_adapter *a, struct atto_csmi *ci)
{
	struct esas2r_buffered_ioctl bi;

	memset(&bi, 0, sizeof(bi));

	bi.a = a;
	bi.ioctl = &ci->data;
	bi.length = sizeof(union atto_ioctl_csmi);
	bi.offset = 0;
	bi.callback = csmi_ioctl_callback;
	bi.context = ci;
	bi.done_callback = csmi_ioctl_done_callback;
	bi.done_context = ci;

	return handle_buffered_ioctl(&bi);
}