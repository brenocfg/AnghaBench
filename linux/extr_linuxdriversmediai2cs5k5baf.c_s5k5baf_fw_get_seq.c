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
typedef  scalar_t__ u16 ;
struct s5k5baf_fw {int count; TYPE_1__* seq; scalar_t__* data; } ;
struct s5k5baf {struct s5k5baf_fw* fw; } ;
struct TYPE_2__ {scalar_t__ id; int offset; } ;

/* Variables and functions */

__attribute__((used)) static u16 *s5k5baf_fw_get_seq(struct s5k5baf *state, u16 seq_id)
{
	struct s5k5baf_fw *fw = state->fw;
	u16 *data;
	int i;

	if (fw == NULL)
		return NULL;

	data = fw->data + 2 * fw->count;

	for (i = 0; i < fw->count; ++i) {
		if (fw->seq[i].id == seq_id)
			return data + fw->seq[i].offset;
	}

	return NULL;
}