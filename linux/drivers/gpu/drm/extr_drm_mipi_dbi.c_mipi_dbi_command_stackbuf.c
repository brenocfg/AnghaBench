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
struct mipi_dbi {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int mipi_dbi_command_stackbuf(struct mipi_dbi *dbi, u8 cmd, u8 *data, size_t len)
{
	u8 *buf;
	int ret;

	buf = kmemdup(data, len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = mipi_dbi_command_buf(dbi, cmd, buf, len);

	kfree(buf);

	return ret;
}