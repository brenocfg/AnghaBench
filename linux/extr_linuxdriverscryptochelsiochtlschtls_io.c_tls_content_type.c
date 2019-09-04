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
 unsigned char CPL_TX_TLS_SFO_TYPE_ALERT ; 
 unsigned char CPL_TX_TLS_SFO_TYPE_CCS ; 
 unsigned char CPL_TX_TLS_SFO_TYPE_DATA ; 
 unsigned char CPL_TX_TLS_SFO_TYPE_HANDSHAKE ; 
 unsigned char CPL_TX_TLS_SFO_TYPE_HEARTBEAT ; 
#define  TLS_HDR_TYPE_ALERT 131 
#define  TLS_HDR_TYPE_CCS 130 
#define  TLS_HDR_TYPE_HANDSHAKE 129 
#define  TLS_HDR_TYPE_HEARTBEAT 128 

__attribute__((used)) static unsigned char tls_content_type(unsigned char content_type)
{
	switch (content_type) {
	case TLS_HDR_TYPE_CCS:
		return CPL_TX_TLS_SFO_TYPE_CCS;
	case TLS_HDR_TYPE_ALERT:
		return CPL_TX_TLS_SFO_TYPE_ALERT;
	case TLS_HDR_TYPE_HANDSHAKE:
		return CPL_TX_TLS_SFO_TYPE_HANDSHAKE;
	case TLS_HDR_TYPE_HEARTBEAT:
		return CPL_TX_TLS_SFO_TYPE_HEARTBEAT;
	}
	return CPL_TX_TLS_SFO_TYPE_DATA;
}