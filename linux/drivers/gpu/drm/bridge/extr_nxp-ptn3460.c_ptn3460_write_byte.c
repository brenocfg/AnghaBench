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
struct ptn3460_bridge {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptn3460_write_byte(struct ptn3460_bridge *ptn_bridge, char addr,
		char val)
{
	int ret;
	char buf[2];

	buf[0] = addr;
	buf[1] = val;

	ret = i2c_master_send(ptn_bridge->client, buf, ARRAY_SIZE(buf));
	if (ret <= 0) {
		DRM_ERROR("Failed to send i2c command, ret=%d\n", ret);
		return ret;
	}

	return 0;
}