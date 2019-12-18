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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ddb_link {int /*<<< orphan*/  nr; struct ddb* dev; } ;
struct ddb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ddbridge_flashread (struct ddb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxl_fw_read(void *priv, u8 *buf, u32 len)
{
	struct ddb_link *link = priv;
	struct ddb *dev = link->dev;

	dev_info(dev->dev, "Read mxl_fw from link %u\n", link->nr);

	return ddbridge_flashread(dev, link->nr, buf, 0xc0000, len);
}