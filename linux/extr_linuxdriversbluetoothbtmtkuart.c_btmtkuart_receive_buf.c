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
typedef  int /*<<< orphan*/  u8 ;
struct serdev_device {int dummy; } ;
struct btmtkuart_dev {TYPE_2__* hdev; } ;
struct TYPE_3__ {size_t byte_rx; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int btmtkuart_recv (TYPE_2__*,int /*<<< orphan*/  const*,size_t) ; 
 struct btmtkuart_dev* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static int btmtkuart_receive_buf(struct serdev_device *serdev, const u8 *data,
				 size_t count)
{
	struct btmtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	int err;

	err = btmtkuart_recv(bdev->hdev, data, count);
	if (err < 0)
		return err;

	bdev->hdev->stat.byte_rx += count;

	return count;
}