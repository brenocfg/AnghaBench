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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int TRANSCODER_DSI_A ; 
 int TRANSCODER_DSI_C ; 

__attribute__((used)) static inline bool transcoder_is_dsi(enum transcoder transcoder)
{
	return transcoder == TRANSCODER_DSI_A || transcoder == TRANSCODER_DSI_C;
}