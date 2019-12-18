#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_3__ {unsigned char key; } ;

/* Variables and functions */
 unsigned int CTRLCHAR_CTRL ; 
 unsigned int CTRLCHAR_NONE ; 
 unsigned int CTRLCHAR_SYSRQ ; 
 unsigned int EOF_CHAR (struct tty_struct*) ; 
 unsigned int INTR_CHAR (struct tty_struct*) ; 
 unsigned int SUSP_CHAR (struct tty_struct*) ; 
 TYPE_1__ ctrlchar_sysrq ; 
 int /*<<< orphan*/  schedule_sysrq_work (TYPE_1__*) ; 
 int tolower (unsigned char const) ; 

unsigned int
ctrlchar_handle(const unsigned char *buf, int len, struct tty_struct *tty)
{
	if ((len < 2) || (len > 3))
		return CTRLCHAR_NONE;

	/* hat is 0xb1 in codepage 037 (US etc.) and thus */
	/* converted to 0x5e in ascii ('^') */
	if ((buf[0] != '^') && (buf[0] != '\252'))
		return CTRLCHAR_NONE;

#ifdef CONFIG_MAGIC_SYSRQ
	/* racy */
	if (len == 3 && buf[1] == '-') {
		ctrlchar_sysrq.key = buf[2];
		schedule_sysrq_work(&ctrlchar_sysrq);
		return CTRLCHAR_SYSRQ;
	}
#endif

	if (len != 2)
		return CTRLCHAR_NONE;

	switch (tolower(buf[1])) {
	case 'c':
		return INTR_CHAR(tty) | CTRLCHAR_CTRL;
	case 'd':
		return EOF_CHAR(tty)  | CTRLCHAR_CTRL;
	case 'z':
		return SUSP_CHAR(tty) | CTRLCHAR_CTRL;
	}
	return CTRLCHAR_NONE;
}