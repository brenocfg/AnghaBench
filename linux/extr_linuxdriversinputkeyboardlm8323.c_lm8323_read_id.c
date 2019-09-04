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
struct lm8323_chip {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LM8323_CMD_READ_ID ; 
 int lm8323_read (struct lm8323_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lm8323_read_id(struct lm8323_chip *lm, u8 *buf)
{
	int bytes;

	bytes = lm8323_read(lm, LM8323_CMD_READ_ID, buf, 2);
	if (unlikely(bytes != 2))
		return -EIO;

	return 0;
}