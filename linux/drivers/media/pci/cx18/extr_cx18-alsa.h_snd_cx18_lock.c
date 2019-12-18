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
struct snd_cx18_card {int /*<<< orphan*/  v4l2_dev; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct cx18* to_cx18 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_cx18_lock(struct snd_cx18_card *cxsc)
{
	struct cx18 *cx = to_cx18(cxsc->v4l2_dev);
	mutex_lock(&cx->serialize_lock);
}