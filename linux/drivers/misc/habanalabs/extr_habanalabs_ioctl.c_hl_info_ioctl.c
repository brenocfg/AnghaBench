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
struct hl_fpriv {TYPE_1__* hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int _hl_info_ioctl (struct hl_fpriv*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hl_info_ioctl(struct hl_fpriv *hpriv, void *data)
{
	return _hl_info_ioctl(hpriv, data, hpriv->hdev->dev);
}