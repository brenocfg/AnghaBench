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
 int /*<<< orphan*/  sclp_tty_chars ; 
 scalar_t__ sclp_tty_chars_count ; 
 int /*<<< orphan*/  sclp_tty_write_string (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sclp_tty_flush_buffer(struct tty_struct *tty)
{
	if (sclp_tty_chars_count > 0) {
		sclp_tty_write_string(sclp_tty_chars, sclp_tty_chars_count, 0);
		sclp_tty_chars_count = 0;
	}
}