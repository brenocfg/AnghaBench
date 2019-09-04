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
struct cmdline_parts {struct cmdline_parts* next_parts; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmdline_parts_free (struct cmdline_parts**) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int parse_parts (struct cmdline_parts**,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 char* strchr (char*,char) ; 

int cmdline_parts_parse(struct cmdline_parts **parts, const char *cmdline)
{
	int ret;
	char *buf;
	char *pbuf;
	char *next;
	struct cmdline_parts **next_parts;

	*parts = NULL;

	next = pbuf = buf = kstrdup(cmdline, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	next_parts = parts;

	while (next && *pbuf) {
		next = strchr(pbuf, ';');
		if (next)
			*next = '\0';

		ret = parse_parts(next_parts, pbuf);
		if (ret)
			goto fail;

		if (next)
			pbuf = ++next;

		next_parts = &(*next_parts)->next_parts;
	}

	if (!*parts) {
		pr_warn("cmdline partition has no valid partition.");
		ret = -EINVAL;
		goto fail;
	}

	ret = 0;
done:
	kfree(buf);
	return ret;

fail:
	cmdline_parts_free(parts);
	goto done;
}