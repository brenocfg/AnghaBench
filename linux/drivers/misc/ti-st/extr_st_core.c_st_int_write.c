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
struct tty_struct {TYPE_1__* ops; } ;
struct st_data_s {struct tty_struct* tty; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,unsigned char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned char const*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct tty_struct*,unsigned char const*,int) ; 
 scalar_t__ unlikely (int) ; 

int st_int_write(struct st_data_s *st_gdata,
	const unsigned char *data, int count)
{
	struct tty_struct *tty;
	if (unlikely(st_gdata == NULL || st_gdata->tty == NULL)) {
		pr_err("tty unavailable to perform write");
		return -EINVAL;
	}
	tty = st_gdata->tty;
#ifdef VERBOSE
	print_hex_dump(KERN_DEBUG, "<out<", DUMP_PREFIX_NONE,
		16, 1, data, count, 0);
#endif
	return tty->ops->write(tty, data, count);

}