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
struct tb_switch {TYPE_2__* tb; TYPE_1__* nvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {unsigned int buf_data_size; scalar_t__ buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NVM_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 
 scalar_t__ vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_switch_nvm_write(void *priv, unsigned int offset, void *val,
			       size_t bytes)
{
	struct tb_switch *sw = priv;
	int ret = 0;

	if (!mutex_trylock(&sw->tb->lock))
		return restart_syscall();

	/*
	 * Since writing the NVM image might require some special steps,
	 * for example when CSS headers are written, we cache the image
	 * locally here and handle the special cases when the user asks
	 * us to authenticate the image.
	 */
	if (!sw->nvm->buf) {
		sw->nvm->buf = vmalloc(NVM_MAX_SIZE);
		if (!sw->nvm->buf) {
			ret = -ENOMEM;
			goto unlock;
		}
	}

	sw->nvm->buf_data_size = offset + bytes;
	memcpy(sw->nvm->buf + offset, val, bytes);

unlock:
	mutex_unlock(&sw->tb->lock);

	return ret;
}