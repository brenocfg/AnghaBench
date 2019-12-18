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

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
#define  PIPE_ERROR_AGAIN 130 
#define  PIPE_ERROR_IO 129 
#define  PIPE_ERROR_NOMEM 128 

__attribute__((used)) static int goldfish_pipe_error_convert(int status)
{
	switch (status) {
	case PIPE_ERROR_AGAIN:
		return -EAGAIN;
	case PIPE_ERROR_NOMEM:
		return -ENOMEM;
	case PIPE_ERROR_IO:
		return -EIO;
	default:
		return -EINVAL;
	}
}