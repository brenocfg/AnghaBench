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
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
struct TYPE_3__ {int buffer_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INT_ENABLE ; 
 int /*<<< orphan*/  AUDIO_INT_MASK ; 
 int AUDIO_INT_WRITE_BUFFER_1_EMPTY ; 
 int AUDIO_INT_WRITE_BUFFER_2_EMPTY ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_1__* audio_data ; 
 int /*<<< orphan*/  audio_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_count ; 

__attribute__((used)) static int goldfish_audio_open(struct inode *ip, struct file *fp)
{
	if (!audio_data)
		return -ENODEV;

	if (atomic_inc_return(&open_count) == 1) {
		fp->private_data = audio_data;
		audio_data->buffer_status = (AUDIO_INT_WRITE_BUFFER_1_EMPTY |
					     AUDIO_INT_WRITE_BUFFER_2_EMPTY);
		audio_write(audio_data, AUDIO_INT_ENABLE, AUDIO_INT_MASK);
		return 0;
	}

	atomic_dec(&open_count);
	return -EBUSY;
}