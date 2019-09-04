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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr_id ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 

__attribute__((used)) static int nfcon_tty_put_char(struct tty_struct *tty, unsigned char ch)
{
	char temp[2] = { ch, 0 };

	nf_call(stderr_id, virt_to_phys(temp));
	return 1;
}