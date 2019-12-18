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
typedef  int /*<<< orphan*/  va_list ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PRINTF_BUFFER_SIZE ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  vsnprintf (char*,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_write (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void xenbus_va_dev_error(struct xenbus_device *dev, int err,
				const char *fmt, va_list ap)
{
	unsigned int len;
	char *printf_buffer;
	char *path_buffer;

#define PRINTF_BUFFER_SIZE 4096

	printf_buffer = kmalloc(PRINTF_BUFFER_SIZE, GFP_KERNEL);
	if (!printf_buffer)
		return;

	len = sprintf(printf_buffer, "%i ", -err);
	vsnprintf(printf_buffer + len, PRINTF_BUFFER_SIZE - len, fmt, ap);

	dev_err(&dev->dev, "%s\n", printf_buffer);

	path_buffer = kasprintf(GFP_KERNEL, "error/%s", dev->nodename);
	if (path_buffer)
		xenbus_write(XBT_NIL, path_buffer, "error", printf_buffer);

	kfree(printf_buffer);
	kfree(path_buffer);
}