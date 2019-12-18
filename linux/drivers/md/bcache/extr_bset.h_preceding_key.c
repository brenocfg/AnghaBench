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
struct bkey {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 struct bkey KEY (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_INODE (struct bkey*) ; 
 scalar_t__ KEY_OFFSET (struct bkey*) ; 

__attribute__((used)) static inline void preceding_key(struct bkey *k, struct bkey **preceding_key_p)
{
	if (KEY_INODE(k) || KEY_OFFSET(k)) {
		(**preceding_key_p) = KEY(KEY_INODE(k), KEY_OFFSET(k), 0);
		if (!(*preceding_key_p)->low)
			(*preceding_key_p)->high--;
		(*preceding_key_p)->low--;
	} else {
		(*preceding_key_p) = NULL;
	}
}