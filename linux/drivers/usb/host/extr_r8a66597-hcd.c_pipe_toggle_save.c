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
struct urb {int dummy; } ;
struct r8a66597_pipe {int /*<<< orphan*/  pipectr; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int SQMON ; 
 int /*<<< orphan*/  pipe_toggle_set (struct r8a66597*,struct r8a66597_pipe*,struct urb*,int) ; 
 int r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_toggle_save(struct r8a66597 *r8a66597,
			     struct r8a66597_pipe *pipe,
			     struct urb *urb)
{
	if (r8a66597_read(r8a66597, pipe->pipectr) & SQMON)
		pipe_toggle_set(r8a66597, pipe, urb, 1);
	else
		pipe_toggle_set(r8a66597, pipe, urb, 0);
}