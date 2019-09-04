#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct hfi_sfr* kva; } ;
struct venus_hfi_device {TYPE_2__ sfr; TYPE_1__* core; } ;
struct hfi_sfr {char* data; int buf_size; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,char*) ; 
 void* memchr (char*,char,int) ; 

__attribute__((used)) static void venus_sfr_print(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	struct hfi_sfr *sfr = hdev->sfr.kva;
	void *p;

	if (!sfr)
		return;

	p = memchr(sfr->data, '\0', sfr->buf_size);
	/*
	 * SFR isn't guaranteed to be NULL terminated since SYS_ERROR indicates
	 * that Venus is in the process of crashing.
	 */
	if (!p)
		sfr->data[sfr->buf_size - 1] = '\0';

	dev_err_ratelimited(dev, "SFR message from FW: %s\n", sfr->data);
}