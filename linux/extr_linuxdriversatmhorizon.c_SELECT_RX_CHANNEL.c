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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CHANNEL_PORT_OFF ; 
 int /*<<< orphan*/  wr_regw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void SELECT_RX_CHANNEL (hrz_dev * dev, u16 channel) {
  wr_regw (dev, RX_CHANNEL_PORT_OFF, channel);
  return;
}