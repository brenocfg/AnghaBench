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
struct x25_asy {scalar_t__ magic; TYPE_2__* dev; int /*<<< orphan*/  flags; } ;
struct tty_struct {struct x25_asy* disc_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLF_ERROR ; 
 scalar_t__ X25_ASY_MAGIC ; 
 int /*<<< orphan*/  netif_running (TYPE_2__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_asy_unesc (struct x25_asy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x25_asy_receive_buf(struct tty_struct *tty,
				const unsigned char *cp, char *fp, int count)
{
	struct x25_asy *sl = tty->disc_data;

	if (!sl || sl->magic != X25_ASY_MAGIC || !netif_running(sl->dev))
		return;


	/* Read the characters out of the buffer */
	while (count--) {
		if (fp && *fp++) {
			if (!test_and_set_bit(SLF_ERROR, &sl->flags))
				sl->dev->stats.rx_errors++;
			cp++;
			continue;
		}
		x25_asy_unesc(sl, *cp++);
	}
}