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
struct cx231xx {size_t model; int /*<<< orphan*/  board; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cx231xx_boards ; 

__attribute__((used)) static inline void cx231xx_set_model(struct cx231xx *dev)
{
	dev->board = cx231xx_boards[dev->model];
}