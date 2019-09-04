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
struct request_queue {int /*<<< orphan*/  queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_ProcessRequest (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DAC960_RequestFunction(struct request_queue *RequestQueue)
{
	DAC960_ProcessRequest(RequestQueue->queuedata);
}