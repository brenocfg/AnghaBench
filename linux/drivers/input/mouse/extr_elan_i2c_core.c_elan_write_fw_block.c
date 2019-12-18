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
typedef  int /*<<< orphan*/  u16 ;
struct elan_tp_data {TYPE_2__* client; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* write_fw_block ) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ETP_RETRY_COUNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int elan_write_fw_block(struct elan_tp_data *data,
			       const u8 *page, u16 checksum, int idx)
{
	int retry = ETP_RETRY_COUNT;
	int error;

	do {
		error = data->ops->write_fw_block(data->client,
						  page, checksum, idx);
		if (!error)
			return 0;

		dev_dbg(&data->client->dev,
			"IAP retrying page %d (error: %d)\n", idx, error);
	} while (--retry > 0);

	return error;
}