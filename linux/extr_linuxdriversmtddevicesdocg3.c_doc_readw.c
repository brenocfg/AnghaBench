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
struct docg3 {TYPE_1__* cascade; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ readw (scalar_t__) ; 
 int /*<<< orphan*/  trace_docg3_io (int /*<<< orphan*/ ,int,scalar_t__,int) ; 

__attribute__((used)) static inline u16 doc_readw(struct docg3 *docg3, u16 reg)
{
	u16 val = readw(docg3->cascade->base + reg);

	trace_docg3_io(0, 16, reg, (int)val);
	return val;
}