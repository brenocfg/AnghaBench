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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct _adapter {struct firmware* fw; TYPE_1__* pnetdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u32 rtl871x_open_fw(struct _adapter *adapter, const u8 **mappedfw)
{
	const struct firmware **raw = &adapter->fw;

	if (adapter->fw->size > 200000) {
		dev_err(&adapter->pnetdev->dev, "r8172u: Badfw->size of %d\n",
			(int)adapter->fw->size);
		return 0;
	}
	*mappedfw = (*raw)->data;
	return (*raw)->size;
}