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
struct cx18_stream {int dummy; } ;
struct cx18_queue {int dummy; } ;
struct cx18_mdl {int dummy; } ;

/* Variables and functions */
 struct cx18_queue* _cx18_enqueue (struct cx18_stream*,struct cx18_mdl*,struct cx18_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct cx18_queue *cx18_enqueue(struct cx18_stream *s, struct cx18_mdl *mdl,
				struct cx18_queue *q)
{
	return _cx18_enqueue(s, mdl, q, 0); /* FIFO */
}