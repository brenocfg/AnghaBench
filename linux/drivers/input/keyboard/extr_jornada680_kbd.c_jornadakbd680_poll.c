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
struct jornadakbd {int /*<<< orphan*/  new_scan; int /*<<< orphan*/  old_scan; } ;
struct input_polled_dev {struct jornadakbd* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  JORNADA_SCAN_SIZE ; 
 int /*<<< orphan*/  jornada_parse_kbd (struct jornadakbd*) ; 
 int /*<<< orphan*/  jornada_scan_keyb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jornadakbd680_poll(struct input_polled_dev *dev)
{
	struct jornadakbd *jornadakbd = dev->private;

	jornada_scan_keyb(jornadakbd->new_scan);
	jornada_parse_kbd(jornadakbd);
	memcpy(jornadakbd->old_scan, jornadakbd->new_scan, JORNADA_SCAN_SIZE);
}