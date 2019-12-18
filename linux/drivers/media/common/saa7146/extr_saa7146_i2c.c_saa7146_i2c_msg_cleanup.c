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
struct i2c_msg {int len; int* buf; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7146_i2c_msg_cleanup(const struct i2c_msg *m, int num, __le32 *op)
{
	int i, j;
	int op_count = 0;

	/* loop through all messages */
	for(i = 0; i < num; i++) {

		op_count++;

		/* loop through all bytes of message i */
		for(j = 0; j < m[i].len; j++) {
			/* write back all bytes that could have been read */
			m[i].buf[j] = (le32_to_cpu(op[op_count/3]) >> ((3-(op_count%3))*8));
			op_count++;
		}
	}

	return 0;
}